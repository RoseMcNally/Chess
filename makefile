chess: main.o ChessBoard.o Square.o Piece.o Pawn.o Bishop.o Knight.o \
Rook.o Queen.o King.o Player.o errors.o
	g++ -Wall -Wextra -g main.o ChessBoard.o Square.o Piece.o Pawn.o \
Bishop.o Knight.o Rook.o Queen.o King.o Player.o errors.o -o chess

main.o: ChessMain.cpp ChessBoard.h
	g++ -c -Wall -Wextra -g ChessMain.cpp -o main.o

ChessBoard.o: ChessBoard.cpp ChessBoard.h Piece.h Pawn.h Bishop.h Knight.h \
Rook.h Queen.h King.h Square.h Player.h constants.h
	g++ -c -Wall -Wextra -g ChessBoard.cpp -o ChessBoard.o

Piece.o: Piece.cpp Piece.h ChessBoard.h Square.h Player.h constants.h
	g++ -c -Wall -Wextra -g Piece.cpp -o Piece.o

Pawn.o: Pawn.cpp Pawn.h Piece.h ChessBoard.h Square.h Player.h constants.h
	g++ -c -Wall -Wextra -g Pawn.cpp -o Pawn.o

Bishop.o: Bishop.cpp Bishop.h Piece.h ChessBoard.h Square.h Player.h constants.h
	g++ -c -Wall -Wextra -g Bishop.cpp -o Bishop.o

Knight.o: Knight.cpp Knight.h Piece.h ChessBoard.h Square.h Player.h constants.h
	g++ -c -Wall -Wextra -g Knight.cpp -o Knight.o

Rook.o: Rook.cpp Rook.h Piece.h ChessBoard.h Square.h Player.h constants.h
	g++ -c -Wall -Wextra -g Rook.cpp -o Rook.o

Queen.o: Queen.cpp Queen.h Piece.h ChessBoard.h Square.h Player.h constants.h
	g++ -c -Wall -Wextra -g Queen.cpp -o Queen.o

King.o: King.cpp King.h Piece.h ChessBoard.h Square.h Player.h constants.h
	g++ -c -Wall -Wextra -g King.cpp -o King.o

Square.o: Square.cpp Square.h constants.h errors.h
	g++ -c -Wall -Wextra -g Square.cpp -o Square.o

Player.o: Player.cpp Player.h
	g++ -c -Wall -Wextra -g Player.cpp -o Player.o

errors.o: errors.cpp errors.h
	g++ -c -Wall -Wextra -g errors.cpp -o errors.o

clean:
	rm *.o chess
