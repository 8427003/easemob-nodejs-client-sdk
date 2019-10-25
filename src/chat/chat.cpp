#include "chat.h"
#include "message/emmessage.h"
#include "message/emtextmessagebody.h"
#include "emclient.h"
#include "emchatmanager_interface.h"
#include "emchatroommanager_interface.h"
#include "emcallback.h"
#include "emerror.h"
#include <string>
#include <vector>
#include <thread>
#include <iostream>
#include <list>

#ifdef __linux__
#include "unistd.h"
#include <string.h>       // strncpy
#include <sys/ioctl.h>    // SIOCGIFFLAGS
#include <errno.h>        // errno
#include <netinet/in.h>   //IPPROTO_IP
#include <net/if.h>       // IFF_*, ifreq
#include <linux/sockios.h>
#include <linux/ethtool.h>
#endif


using namespace easemob;

namespace NodeChat {

using std::string;
using std::stringstream;
using std::list;
using std::vector;
using std::endl;
using std::cout;

using easemob::EMError;
using easemob::EMClient;
using easemob::EMChatManagerInterface;
using easemob::EMChatroomManagerInterface;

Chat::Chat(const std::string &resourcePath, const std::string &workPath, const std::string &appKey)
{
    log_file_.open (workPath + "/log");
    easemob::EMChatConfigsPtr configPtr = easemob::EMChatConfigsPtr(new easemob::EMChatConfigs(resourcePath, workPath, appKey));
    configPtr->setEnableConsoleLog(false);
    chatClient = easemob::EMClient::create(configPtr);
    chatClient->getChatManager().addListener(this);
    chatClient->addConnectionListener(this);
}

Chat::~Chat()
{
    chatClient->removeConnectionListener(this);
    chatClient->getChatManager().removeListener(this);
    log_file_.close();
    delete chatClient;
}

void Chat::onConnect()
{
}

void Chat::onDisconnect(easemob::EMErrorPtr error)
{

}

void Chat::onPong()
{

}

void Chat::onReceiveMessages(const easemob::EMMessageList &messages)
{
    std::cout << "onreceive...." <<std::endl;
    if(messages.size() > 0) {
        for(auto m: messages) { 
            if (m->bodies().size() > 0 && m->bodies()[0]->type() == easemob::EMMessageBody::TEXT)
            {
                string text = static_cast<easemob::EMTextMessageBody*>(m->bodies()[0].get())->text();
		if(_handleReceiveMessage != NULL) {
		    string userinfo;
		    m->getAttribute("userInfo", userinfo);
		   _handleReceiveMessage(text, m->from(), m->to(), "text", userinfo);
		}
            }
        }
    }
}

void Chat::onReceiveError(const easemob::EMMessagePtr message, const easemob::EMErrorPtr error) {
    std::cout << "onreceiveerror..." <<std::endl;
	_handleReceiveError("");
    //("---> onReceiveError");
}

int Chat::joinChatroom(const std::string &roomId)
{
	easemob::EMError r;
	chatClient->getChatroomManager().joinChatroom(roomId, r);
	if(r.mErrorCode == EMError::EM_NO_ERROR) {
		return 0;
	}
	return -1;
}

int Chat::leaveChatroom(const std::string &roomId)
{
	easemob::EMError r;
	chatClient->getChatroomManager().leaveChatroom(roomId, r);
	if(r.mErrorCode == EMError::EM_NO_ERROR) {
		return 0;
	}
	return -1;
}

int Chat::joinedChatroomById(const std::string &roomId)
{
	auto room = chatClient->getChatroomManager().joinedChatroomById(roomId);
	if(room != NULL) {
	    return 0;
	}
	return -1;
}

int Chat::login(
	const std::string &uid,
	const std::string &passwd,
	void (*handleReceiveMessage)(std::string, std::string, std::string, std::string, std::string),
 	void (*handleReceiveError)(std::string) 
 ) {
	easemob::EMErrorPtr result = chatClient->login(uid, passwd);
	if(result->mErrorCode == EMError::EM_NO_ERROR) {
	   _handleReceiveMessage = handleReceiveMessage;
	   _handleReceiveError = handleReceiveError;
	   return 0;
	}
	return -1;
}

void Chat::Log(const string &message)
{
    log_file_ << message << endl;

}
} // namespace Demo

