# Assets Embedded Variables Documentation

Each asset in this documentation represents a file located in the `assets/*` directory. These assets are embedded within the project for efficient management and retrieval.

## Asset Structure

The `Asset` structure is defined as follows:

```c
typedef struct Asset{
    const char *path;
    unsigned char *data;
    int size;
}Asset;
```

- **path**: A constant string representing the path to the asset.
- **data**: A pointer to the asset's data stored as unsigned characters.
- **size**: An integer representing the size of the asset's data.

## Asset Management Functions

### `Asset *get_asset(const char *path);`

This function retrieves an asset by its path. It returns a pointer to an `Asset` structure.

### `DtwStringArray *list_assets_recursively(const char *path);`

This function lists all assets recursively from a given path. It returns a `DtwStringArray` containing the paths of the assets.

### `DtwStringArray *list_assets(const char *path);`

This function lists assets from a given path. It returns a `DtwStringArray` containing the paths of the assets.

These functions are part of the asset management system, allowing for efficient handling and retrieval of embedded assets within the project.