default: demo

UNAME := $(shell sh -c 'uname 2>/dev/null || echo not')

ifeq ($(UNAME),Darwin)
    LIBS := -leasemob -lcurl -lssl -lcrypto -lz -lresolv -lncurses -lsqlite3
else
    LIBS := -pthread -leasemob -lcurl -lssl -lz -lncurses -lsqlite3
endif

LIBDIR := ../../release/
INCDIR := $(LIBDIR)/include

#check cross compile 
ifeq ($(ARCH),arm)
LDFLAGS = -L$(LIBDIR) \
	-L$(LIBDIR)/platform/raspberrypi/lib \
	$(LIBS)
CPPFLAGS = -std=c++11 -Wall -I$(INCDIR) \
	-I$(LIBDIR)/platform/raspberrypi/include \
	-I$(LIBDIR)/platform/raspberrypi/include/ncurses   
else
LDFLAGS = -L$(LIBDIR) $(LIBS)
CPPFLAGS = -std=c++11 -Wall -I$(INCDIR)	
endif

src = $(wildcard *.cpp)
obj = $(src:.cpp=.o)

$(obj): $(LIBDIR)/libeasemob.a

demo: $(obj)
	$(CXX) -o $@ $^ $(LDFLAGS)

run: demo
	./demo

gdb: demo
	gdb demo

$(LIBDIR)/libeasemob.a:
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@ Compile easemobe sdk first @"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@exit 1

.PHONY: clean Parameter
clean:
	rm -rf $(obj) demo rm -rf appdata/ easemobDB/ easemobLog/
Parameter:
	@echo $(ARCH)
	@echo $(CXX)
	@echo $(LDFLAGS)
	@echo $(CPPFLAGS)
