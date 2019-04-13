TARGET=delta-v-to-GTO
OBJECTS=main.o Orbit.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	g++ -o $(TARGET) $(OBJECTS)

clean:
	rm -f $(TARGET) $(OBJECTS)
