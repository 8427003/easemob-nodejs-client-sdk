#include "chat.h"
#include <node.h>
#include <uv.h>

namespace WrappedChat {

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Persistent;
using v8::NewStringType;
using v8::Object;
using v8::Boolean;
using v8::String;
using v8::Function;
using v8::Number;
using v8::Value;
using v8::Context;
using v8::Exception;

NodeChat::Chat *chat = NULL;
Persistent<Function> _onMessage;
Persistent<Function> _onMessageError;
uv_loop_t *loop = uv_default_loop();
uv_async_t async;
    
void callback(uv_async_t *handle); 

void init(const FunctionCallbackInfo<Value>& args) {
    	std::string appkey = std::string(*String::Utf8Value(args[0]->ToString())); 
	chat = new NodeChat::Chat(".", ".", appkey);
}

class Msg {
   public:
	Msg(std::string content, std::string from, std::string to, std::string type) {
		this->_content = const_cast<char*>(content.c_str());
		this->_from = const_cast<char*>(from.c_str());
		this->_to = const_cast<char*>(to.c_str());
		this->_type = const_cast<char*>(type.c_str());
	};
	~Msg() {
		this->_content = NULL;
		this->_from = NULL;
		this->_to = NULL;
		this->_type = NULL;
	};
	char* _content;
	char* _from;
	char* _to;
	char*_type;
};

void callback(uv_async_t *handle) {
	Isolate * isolate = Isolate::GetCurrent();

	// must before  Local<Context> context = isolate->GetCurrentContext();
	// or create scrope error;
	v8::HandleScope handleScope(isolate);
    	Local<Context> context = isolate->GetCurrentContext();

	auto msg = (Msg *)(handle->data);

	const unsigned argc = 4;
	Local<Value> argv[argc] = {
	   String::NewFromUtf8(isolate, msg->_content, NewStringType::kNormal).ToLocalChecked(),
	   String::NewFromUtf8(isolate, msg->_from, NewStringType::kNormal).ToLocalChecked(),
	   String::NewFromUtf8(isolate, msg->_to, NewStringType::kNormal).ToLocalChecked(),
	   String::NewFromUtf8(isolate, msg->_type, NewStringType::kNormal).ToLocalChecked()
	};

	Local<Function>::New(isolate, _onMessage)->Call(context, Null(isolate), argc, argv).ToLocalChecked();
}

void onMessageFunc (std::string content, std::string from, std::string to, std::string type) {
	async.data = (void *) new Msg(content, from, to, type);
	uv_async_send(&async);
}

void onMessageErrorFunc (std::string str) {

}

void login(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    Local<Context> context = isolate->GetCurrentContext();

    std::string uid = std::string(*String::Utf8Value(args[0]->ToString())); 
    std::string passwd = std::string(*String::Utf8Value(args[1]->ToString()));

    Local<Function> onMessage = Local<Function>::Cast(args[2]);
    Local<Function> onMessageError = Local<Function>::Cast(args[3]);

    _onMessage.Reset(isolate, onMessage);
    _onMessageError.Reset(isolate, onMessageError);

    int isSuccess = chat->login(uid, passwd, onMessageFunc, onMessageErrorFunc);

    uv_async_init(loop, &async, callback);
    args.GetReturnValue().Set(Number::New(isolate, (double)isSuccess));
}

void joinChatRoom(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    std::string roomId = std::string(*String::Utf8Value(args[0]->ToString())); 

    int isSuccess = chat->joinChatroom(roomId);
    args.GetReturnValue().Set(Number::New(isolate, (double)isSuccess));
}

void leaveChatRoom(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    std::string roomId = std::string(*String::Utf8Value(args[0]->ToString())); 

    int isSuccess = chat->leaveChatroom(roomId);
    args.GetReturnValue().Set(Number::New(isolate, (double)isSuccess));
}

void joinedChatRoomById(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    std::string roomId = std::string(*String::Utf8Value(args[0]->ToString())); 

    int isSuccess = chat->joinedChatroomById(roomId);
    args.GetReturnValue().Set(Number::New(isolate, (double)isSuccess));
}

void Initialize(Local<Object> exports) {
    NODE_SET_METHOD(exports, "init", init);
    NODE_SET_METHOD(exports, "login", login);
    NODE_SET_METHOD(exports, "joinChatRoom", joinChatRoom);
    NODE_SET_METHOD(exports, "leaveChatRoom", leaveChatRoom);
    NODE_SET_METHOD(exports, "joinedChatRoomById", joinedChatRoomById);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize)

}
