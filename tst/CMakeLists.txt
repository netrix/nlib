
set(NCMDLINEPARSER src/CmdLineParser/nArguments.cpp
				   src/CmdLineParser/nCommandWalker.cpp)

set(NIMAGES src/Images/nBitmap.cpp)

set(NSOCKETS src/Sockets/nSockets.cpp)

set(NFILES ${NCMDLINEPARSER} ${NIMAGES} ${NSOCKETS})

include_directories("../NLibBase")
include_directories(".")
add_library(nlibutilities ${NFILES})

set(NCMDLINEPARSER src/CmdLineParser/nArguments.cpp
				   src/CmdLineParser/nCommandWalker.cpp)

set(NIMAGES src/Images/nBitmap.cpp)

set(NSOCKETS src/Sockets/nSockets.cpp)

set(NFILES ${NCMDLINEPARSER} ${NIMAGES} ${NSOCKETS})

include_directories("../NLibBase")
include_directories(".")
add_library(nlibutilities ${NFILES})
