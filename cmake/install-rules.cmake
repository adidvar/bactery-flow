install(
    TARGETS bactery-flow_exe
    RUNTIME COMPONENT bactery-flow_Runtime
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
