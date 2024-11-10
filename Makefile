main2:
	g++ main2.cpp glad.c stb_image.c VAO.c VBO.c EBO.c texture.c camera.cpp -o $@ -lglfw3

run: main2
	./main2