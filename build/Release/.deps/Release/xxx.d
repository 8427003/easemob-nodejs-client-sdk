cmd_Release/xxx := g++ -pthread -rdynamic -m64 -L/cppnode/src/third_party/easemob  -o Release/xxx -Wl,--start-group ./Release/obj.target/xxx/src/chat/main.o ./Release/obj.target/xxx/src/chat/chat.o -Wl,--end-group -pthread -leasemob -lcurl -lssl -lz -lncurses -lsqlite3