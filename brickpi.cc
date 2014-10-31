// Luc Prieur, 2014

extern "C" {
#include "c_brickpi.h"
}

#include <node.h>

using namespace v8;

Handle<Value> NClearTick(const Arguments& args) {
  HandleScope scope;
  Local<Number> num = Number::New(c_ClearTick());
  return scope.Close(num); 
}

Handle<Value> NBrickPiSetup(const Arguments& args) {
  HandleScope scope;
  Local<Number> num = Number::New(c_BrickPiSetup());
  return scope.Close(num);
}

Handle<Value> NBrickPiSetupSensors(const Arguments& args) {
  HandleScope scope;
  Local<Number> num = Number::New(c_BrickPiSetupSensors());
  return scope.Close(num);
}

Handle<Value> NBrickPiUpdateValues(const Arguments& args) {
  HandleScope scope;
  Local<Number> num = Number::New(c_BrickPiUpdateValues());
  return scope.Close(num);
}

Handle<Value> NSetAddress(const Arguments& args) {
  HandleScope scope;

  if (args.Length() != 2) {
    ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
    return scope.Close(Undefined());
  }

  if (!args[0]->IsNumber() || !args[1]->IsNumber()) {
    ThrowException(Exception::TypeError(String::New("Wrong arguments")));
    return scope.Close(Undefined());
  }

  c_setAddress(args[0]->NumberValue(), args[1]->NumberValue());
  //  return scope.Close();
}

Handle<Value> NSetMotorEnable(const Arguments& args) {
  HandleScope scope;
  if (args.Length() != 1) {
    ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
    return scope.Close(Undefined());
  }

  if (!args[0]->IsNumber()) {
    ThrowException(Exception::TypeError(String::New("Wrong arguments")));
    return scope.Close(Undefined());
  }

  c_setMotorEnable(args[0]->NumberValue());
  // return scope.Close();
}

Handle<Value> NSetMotorSpeed(const Arguments& args) {
  HandleScope scope;

  if (args.Length() != 2) {
    ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
    return scope.Close(Undefined());
  }

  if (!args[0]->IsNumber() || !args[1]->IsNumber()) {
    ThrowException(Exception::TypeError(String::New("Wrong arguments")));
    return scope.Close(Undefined());
  }

  c_setMotorSpeed(args[0]->NumberValue(),args[1]->NumberValue());
  //  return scope.Close();
}

Handle<Value> NGetMotorEnable(const Arguments& args) {
  HandleScope scope;
  if (args.Length() != 1) {
    ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
    return scope.Close(Undefined());
  }

  if (!args[0]->IsNumber()) {
    ThrowException(Exception::TypeError(String::New("Wrong arguments")));
    return scope.Close(Undefined());
  }

  Local<Number> num = Number::New(c_getMotorEnable(args[0]->NumberValue()));
  return scope.Close(num);
}

Handle<Value> NGetEncoder(const Arguments& args) {
  HandleScope scope;
  if (args.Length() != 1) {
    ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
    return scope.Close(Undefined());
  }

  if (!args[0]->IsNumber()) {
    ThrowException(Exception::TypeError(String::New("Wrong arguments")));
    return scope.Close(Undefined());
  }

  Local<Number> num = Number::New(c_getEncoder(args[0]->NumberValue()));
  return scope.Close(num);
}



void init(Handle<Object> exports) {
  exports->Set(String::NewSymbol("ClearTick"),
      FunctionTemplate::New(NClearTick)->GetFunction());
  
  exports->Set(String::NewSymbol("BrickPiSetup"),
	       FunctionTemplate::New(NBrickPiSetup)->GetFunction());

  exports->Set(String::NewSymbol("BrickPiSetupSensors"),
	       FunctionTemplate::New(NBrickPiSetupSensors)->GetFunction());

  exports->Set(String::NewSymbol("BrickPiUpdateValues"),
               FunctionTemplate::New(NBrickPiUpdateValues)->GetFunction());

  exports->Set(String::NewSymbol("SetAddress"),
               FunctionTemplate::New(NSetAddress)->GetFunction());

  exports->Set(String::NewSymbol("SetMotorEnable"),
               FunctionTemplate::New(NSetMotorEnable)->GetFunction());

  exports->Set(String::NewSymbol("SetMotorSpeed"),
               FunctionTemplate::New(NSetMotorSpeed)->GetFunction());

  exports->Set(String::NewSymbol("GetEncoder"),
               FunctionTemplate::New(NGetEncoder)->GetFunction());


  exports->Set(String::NewSymbol("GetMotorEnable"),
               FunctionTemplate::New(NGetMotorEnable)->GetFunction());
}

NODE_MODULE(brickpi, init)