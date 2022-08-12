

#aux_source_directory(. DIR_SRCS)
     

     

     

# 指定生成目标  
#add_executable(Engine ${DIR_SRCS})

file(GLOB TEST_RESULT LIST_DIRECT false *.cpp)


add_executable (MovanStudio TEST_RESULT)