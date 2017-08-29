OBJECT_FILES   = IPUtils.o jhash.o rtree.o RandomPermute.o CompTool.o 
EXEC_NAME      = CompTool
COMPILE        = g++ -g -c -O0 -Wall -Wextra -std=c++0x
LINK           = g++ -g -o $(EXEC_NAME) -O0 -Wall -Wextra -std=c++0x

all : $(EXEC_NAME)

$(EXEC_NAME) : $(OBJECT_FILES)
	$(LINK) $(OBJECT_FILES)

clean :
	rm -f $(OBJECT_FILES)

spotless : clean
	rm -f $(EXEC_NAME)

CompTool.o : CompTool.cpp
	$(COMPILE) $<

IPUtils.o : IPUtils.cpp
	$(COMPILE) $<

jhash.o : jhash.cpp
	$(COMPILE) $<

RandomPermute.o : RandomPermute.cpp
	$(COMPILE) $<

rtree.o : rtree.cpp
	$(COMPILE) $<
