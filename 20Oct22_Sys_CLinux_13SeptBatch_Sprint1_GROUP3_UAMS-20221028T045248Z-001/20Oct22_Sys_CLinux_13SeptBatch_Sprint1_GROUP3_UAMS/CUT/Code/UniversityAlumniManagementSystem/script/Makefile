CC = gcc

INC = inc
OBJ = obj
SRC = src
BIN = bin
LDFLAGS = -o
CFLAGS = -c -g -Wall
IFLAGS = -I $(INC)/

all: $(BIN)/app

$(BIN)/app: $(OBJ)/admin.o $(OBJ)/alumni.o $(OBJ)/main.o $(OBJ)/student.o $(OBJ)/validations.o
	$(CC) $(LDFLAGS) $(BIN)/app $(OBJ)/admin.o $(OBJ)/alumni.o $(OBJ)/main.o $(OBJ)/student.o $(OBJ)/validations.o

$(OBJ)/admin.o: $(SRC)/admin.c
	$(CC) $(CFLAGS) $(SRC)/admin.c $(IFLAGS)
	mv *.o $(OBJ)/

$(OBJ)/alumni.o: $(SRC)/alumni.c
	$(CC) $(CFLAGS) $(SRC)/alumni.c $(IFLAGS)
	mv *.o $(OBJ)/

$(OBJ)/main.o: $(SRC)/main.c
	$(CC) $(CFLAGS) $(SRC)/main.c $(IFLAGS)
	mv *.o $(OBJ)/

$(OBJ)/student.o: $(SRC)/student.c
	$(CC) $(CFLAGS) $(SRC)/student.c $(IFLAGS)
	mv *.o $(OBJ)/

$(OBJ)/validations.o: $(SRC)/validations.c
	$(CC) $(CFLAGS) $(SRC)/validations.c $(IFLAGS)
	mv *.o $(OBJ)/

clean:
	rm -f a.out *.o
	rm -f $(BIN)/*
	rm -f $(OBJ)/*.o
	@echo "Cleaning Done!"
