OBJS=main.o variable.o interpreter.o function.o calculator.o exception.o
main: $(OBJS)
	g++ -g -std=c++11 $(OBJS)
main.o: main.cpp variable.h interpreter.h function.h calculator.h exception.h
	g++ -std=c++11 -g -c main.cpp variable.h interpreter.h function.h calculator.h exception.h
variable.o: variable.cpp variable.h exception.h
	g++ -std=c++11 -g -c variable.cpp variable.h exception.h
interpreter.o: interpreter.cpp interpreter.h
	g++ -std=c++11 -g -c interpreter.cpp interpreter.h
function.o: function.cpp function.h interpreter.h calculator.h
	g++ -std=c++11 -g -c function.cpp function.h interpreter.h calculator.h
calculator.o: calculator.cpp calculator.h function.h variable.h exception.h
	g++ -std=c++11 -g -c calculator.cpp calculator.h function.h variable.h exception.h
exception.o: exception.cpp exception.h
	g++ -std=c++11 -g -c exception.cpp exception.h
clean:
	del edit $(OBJS)