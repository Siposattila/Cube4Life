default: all

.PHONY: all shader
all: run

run: shader
	cmkr build
	./build/Cube4Life

shader:
	mkdir -p ./shader/compiled
	glslc ./shader/raw/triangle/shader.vert -o ./shader/compiled/triangle_vert.spv
	glslc ./shader/raw/triangle/shader.frag -o ./shader/compiled/triangle_frag.spv
