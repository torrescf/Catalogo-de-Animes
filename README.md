
# Anime Catalog

This is a project for managing anime records, developed to apply fundamental programming concepts such as dynamic memory allocation, sorting and searching algorithms, and file manipulation.

## Features

- **Dynamic Memory Allocation:**  
  The array that stores anime records uses dynamic allocation, allowing the program to expand its capacity as new anime entries are added.

- **Sorting with Quick Sort:**  
  Implementation of the Quick Sort algorithm to organize the records, making it easier to query and maintain the data.

- **Binary Search:**  
  Efficiently locates specific records in the catalog, improving performance in searches.

- **Data Persistence:**  
  Reading and writing records to files to ensure that the data is retained between program executions.

- **Adding New Anime:**  
  Allows users to expand the catalog with new anime records.

## Requirements

- C++ compiler compatible with C++11 or higher.
- Windows, Linux, or macOS operating system.

## How to Run the Project

1. Clone the repository:
   ```bash
   git clone https://github.com/torrescf/Catalogo-de-Animes.git
   ```

2. Navigate to the project directory:
   ```bash
   cd Catalogo-de-Animes
   ```

3. Compile the source code:
   ```bash
   g++ -o catalogo main.cpp
   ```

4. Run the program:
   ```bash
   ./catalogo
   ```

## Project Structure

- `main.cpp`:  
  The main file of the program, containing the implementation of the described features.

- `data/`:  
  Directory for storing the persistent data files.

## Future Features

- Implementation of a graphical user interface (GUI) for better usability.
- Exporting records in formats such as CSV or JSON.
- Integration with APIs to automatically fetch anime information.
