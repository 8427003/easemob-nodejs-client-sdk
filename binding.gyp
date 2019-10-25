{
  "targets": [
    {
	    "target_name": "addon",
	    "sources": [ "src/chat/node.cpp", "src/chat/chat.cpp" ],
	    "include_dirs": [
		"src/third_party/easemob/include",
	    	"<!(node -e \"require('nan')\")"
	    ],
	    "cflags": [ "-std=c++11", "-Wall" ],
	    'link_settings': {
		    'library_dirs': [
		    	"/cppnode/src/third_party/easemob"
		    ],
		    'libraries': [
			'-pthread', 
			'-leasemob',
			'-lcurl',
			'-lssl',
			'-lz',
			'-lncurses',
			'-lsqlite3'
		    ]
	    }
    },
    {
	    "target_name": "xxx",
		"type":"executable",
	    "sources": [ "src/chat/main.cpp", "src/chat/chat.cpp" ],
	    "include_dirs": [
		"src/third_party/easemob/include",
	    	"<!(node -e \"require('nan')\")"
	    ],
	    "cflags": [ "-std=c++11", "-Wall" ],
	    'link_settings': {
		    'library_dirs': [
		    	"/cppnode/src/third_party/easemob"
		    ],
		    'libraries': [
			'-pthread', 
			'-leasemob',
			'-lcurl',
			'-lssl',
			'-lz',
			'-lncurses',
			'-lsqlite3'
		    ]
	    }
    }
  ],
}
