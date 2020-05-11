
PROG	= disk-stress
YACC	= bison -y
CFLAGS	= -O3
LIB	= disk-stress.a

$(PROG):	$(LIB)
	$(CC) $(LIB) -lpthread -lm -o $@

$(LIB):		$(LIB)(random-io-thread.o) \
		$(LIB)(sequential-io-thread.o) \
		$(LIB)(random-number.o) \
		$(LIB)(lex-stuff.o) \
		$(LIB)(histo.o) \
		$(LIB)(y.tab.o) \
		$(LIB)($(PROG).o) \
		$(LIB)(thread-support.o)

y.tab.c y.tab.h:	grammar.y
	$(YACC) -d grammar.y

$(LIB)($(PROG).o):		disk-stress.h
$(LIB)(random-io-thread.o):	disk-stress.h
$(LIB)(sequential-io-thread.o):	disk-stress.h
$(LIB)(random-number.o):	disk-stress.h
$(LIB)(histo.o):		histo.h
$(LIB)(lex-stuff.o):		disk-stress.h keyword.h y.tab.h 
$(LIB)(y.tab.o):		disk-stress.h keyword.h y.tab.c
$(LIB)(thread-support.o):	disk-stress.h

clean:
	$(RM) *.[oa] *~ y.tab*

clobber: clean
	$(RM) $(PROG)

install: $(PROG)

