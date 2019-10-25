// hello.cc
#include <node.h>

namespace demo {

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::NewStringType;
using v8::Object;
using v8::Boolean;
using v8::String;
using v8::Number;
using v8::Value;
using v8::Context;
using v8::Exception;

class A {
	public:
		int a;
		A() {
a = 1;
};
		~A() {};
		int aa() {
			return ++a;
		};
};

A *a = new A();

void Method(const FunctionCallbackInfo<Value>& args) {
	;
    Isolate* isolate = args.GetIsolate();

    double value0 = args[0].As<Number>()->Value();
    Local<String> value1 = args[1]->ToString();

    //std::string value1 = String::NewFromUtf8(isolate, , NewStringType::kNormal).ToLocalChecked(),
    //Local<Object> value2 = args[2];

    Local<Context> context = isolate->GetCurrentContext();
    Local<Object> obj = Object::New(isolate);
    obj->Set(context,
            String::NewFromUtf8(isolate, "value0", NewStringType::kNormal).ToLocalChecked(),
            Number::New(isolate, a->aa())
    );

    Local<String> aaa = String::NewFromUtf8(isolate, "mmmm", NewStringType::kNormal).ToLocalChecked();
    v8::String::Utf8Value pp (isolate, aaa);
    char* p1 = *pp;

    obj->Set(context,
            String::NewFromUtf8(isolate, "value1", NewStringType::kNormal).ToLocalChecked(),
            value1
    );

    obj->Set(context,
            String::NewFromUtf8(isolate, "value2", NewStringType::kNormal).ToLocalChecked(),
            Boolean::New(isolate, args[2]->IsObject())
    );

    obj->Set(context,
            String::NewFromUtf8(isolate, "value3", NewStringType::kNormal).ToLocalChecked(),
            Boolean::New(isolate, args[3]->IsArray())
    );

    args.GetReturnValue().Set(obj);
}

void Initialize(Local<Object> exports) {
    NODE_SET_METHOD(exports, "hello", Method);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize)

    }  // namespace demo
