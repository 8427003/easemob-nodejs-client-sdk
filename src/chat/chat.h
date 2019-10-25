#ifndef DEMO_CHAT_H_
#define DEMO_CHAT_H_

#include "emclient.h"
#include "emchatmanager_listener.h"
#include "emcallback.h"

#include <sstream>
#include <string>
#include <fstream>
#include <thread>

namespace NodeChat {

class Chat : public easemob::EMChatManagerListener, public easemob::EMConnectionListener {
public:
    Chat(const std::string &resourcePath, const std::string &workPath, const std::string &appKey);
    ~Chat();

    virtual void onReceiveMessages(const easemob::EMMessageList &messages);
    virtual void onReceiveError(const easemob::EMMessagePtr message, const easemob::EMErrorPtr error);

    void onConnect();
    void onDisconnect(easemob::EMErrorPtr error);
    void onPong();

    int login(
	const std::string &uid,
	const std::string &passwd,
 	void (*handleReceiveMessage)(std::string content, std::string from, std::string to, std::string type, std::string ext),
 	void (*handleReceiveError)(std::string)
    );
    int joinChatroom(const std::string &roomId);
    int leaveChatroom(const std::string &roomId);
    int joinedChatroomById(const std::string &roomId);
private:
    void Log(const std::string &message);
    easemob::EMClient *chatClient;
    void (*_handleReceiveMessage)(std::string content, std::string from, std::string to, std::string type, std::string ext);
    void (*_handleReceiveError)(std::string);

    std::ofstream log_file_;
    std::string loginUser;

    easemob::EMCallbackObserverHandle mHandle;
    
    bool mLogedin;
};


} // namespace Demo

#endif // DEMO_WINDOW_H_
