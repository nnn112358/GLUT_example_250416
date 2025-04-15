CC = g++
CFLAGS = -Wall -g
LDFLAGS = -lglut -lGLU -lGL -lm

TARGET = triangle
SRCS = gl_triangle.cpp

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(TARGET)
