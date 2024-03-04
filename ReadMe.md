# SBUSReader for Raspberry Pi Pico

## Introduction

A simple and easy to use library to read SBUS signals from a Futaba or FrSky receiver using a Raspberry Pi Pico.

## Installation and Usage

This library can easily used as a submodule in a project.

Run the following commands in your project's root directory:

```bash
mkdir external
git submodule add https://github.com/BlackXDragon/SBUSReader.git external/SBUSReader
git submodule update --init
```

Then, add the following lines to your `CMakeLists.txt`:

```cmake
add_subdirectory(external/SBUSReader)
target_link_libraries(${PROJECT_NAME} SBUSReader)
```

## Example

For a simple example on how to use this library, see the `main.cpp` file.

## License

This library is licensed under the MIT License. See the `LICENSE` file for more information.

## Contributing

If you would like to contribute to this project, please open an issue or a pull request. I would be happy to help you out with any questions you may have.