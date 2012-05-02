cmake_minimum_required(VERSION 2.8)
project(NLib)

# Whole program optimization
#set(EXTRA_C_FLAGS_RELEASE ${EXTRA_C_FLAGS_RELEASE} /GL)

# Remove unreferenced functions
#set(EXTRA_C_FLAGS_RELEASE ${EXTRA_C_FLAGS_RELEASE} /Zi)

add_subdirectory(src)
