DEST_DIR := dest
SOURCE_DIR := src

PROJECT_NAME := sfml-project-setuper
EXECUTABLE_NAME := sfml-stpr

.PHONY: all exit clean install-linux zip

all: exit

zip: exit
	cd dest && zip -r $(PROJECT_NAME).zip $(PROJECT_NAME)

install-linux: exit
	sudo cp $(DEST_DIR)/$(PROJECT_NAME)/$(EXECUTABLE_NAME) /usr/bin/$(EXECUTABLE_NAME)

exit: $(DEST_DIR)/$(PROJECT_NAME)/$(EXECUTABLE_NAME)

$(DEST_DIR)/$(PROJECT_NAME)/$(EXECUTABLE_NAME): $(SOURCE_DIR)/main.cpp
	mkdir -p $(DEST_DIR)/$(PROJECT_NAME)
	g++ -o $(DEST_DIR)/$(PROJECT_NAME)/$(EXECUTABLE_NAME) $(SOURCE_DIR)/main.cpp --freestanding

$(exit): $(src)/main.cpp
	g++ -o $(e/xit) $(src)/main.cpp --free-standing

clean:
	rm -rf dest
