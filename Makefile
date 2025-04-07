# Compilador y flags
CXX := g++
CXXFLAGS  := -std=c++11 -Werror -Wall -Wextra -Wshadow -Wconversion -Wfatal-errors -Wpedantic -Wnull-dereference -Wlogical-op -Wduplicated-cond
OPTFLAGS  := -O2 -march=native	# optimizaciones
DBGFLAGS  := -g -fsanitize=address,undefined -DDEBUG
GDBFLAGS  := -g -O0 -DDEBUG

# Intérprete de Python
PYTHON := python
# Ruta del script para dif
COMPARE := compare.py
# Ruta para output1
OUT1 := out1
# Ruta para output2
OUT2 := out2
# Ruta para input
INP := input

# Si se usa DEBUG=1, cambia los flags de optimizacion por los de debug/sanitizers
# ej DEBUG=1 make run file.cpp
ifeq ($(DEBUG), 1)
    CXXFLAGS += $(DBGFLAGS)
else
    CXXFLAGS += $(OPTFLAGS)
endif

.PHONY: run fast debug clean compare gdb

# Obtener el nombre del archivo sin la extensión cpp
FILE := $(basename $(word 2, $(MAKECMDGOALS)))

# Regla para compilar y ejecutar
run: $(FILE)
	@echo "Ejecutando $(FILE)..."
	@./$(FILE)

# Regla para compilar y ejecutar con input
inp: $(FILE)
	@echo "Ejecutando $(FILE) con input..."
	@./$(FILE) < input

# Regla para compilar, ejecutar con input, guardar output y comparar
# Ejecuta el programa con el arhivo $(INP)
# Guarda el resultado en $(OUT1)
# Compara el resultado con lo que haya en $(OUT2) usando el script $(COMPARE)
comp: $(FILE)
	@mkdir -p output
	@echo "Ejecutando $(FILE) con input y guardando output en output1..."
	@./$(FILE) < $(INP) > $(OUT1)
	@$(PYTHON) $(COMPARE) --file1 $(OUT1) --file2 $(OUT2)

# Regla para compilar con flags de DEBUG y ejecutar con GDB usando el input
gdb: $(FILE)-gdb
	@echo "Iniciando GDB para $(FILE)"
	@gdb -ex "run < input" ./$(FILE)-gdb

%-gdb: %.cpp
	@echo "Compilando $< para debug con GDB..."
	$(CXX) $(CXXFLAGS) $(GDBFLAGS) -o $@ $<

# Regla de compilación
%: %.cpp
	@echo "Compilando $<..."
	$(CXX) $(CXXFLAGS) -o $@ $<

# Evita errores cuando `make` intenta interpretar `file.o/cpp` como un objetivo
%.cpp:
	@:
%:
	@:

# Limpia archivos compilados
clean:
	rm -f *.o *.out *.exe *.html $(FILE)	
	@echo cleaning files
	@[ -f $(OUT1) ] && > $(OUT1) || :
	@[ -f $(OUT2) ] && > $(OUT2) || :
	@[ -f $(INP) ] && > $(INP) || :