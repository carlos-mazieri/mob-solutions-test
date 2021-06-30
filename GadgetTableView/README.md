Chosen solution was to create the QObject helper class **GadgetHelper**.

This object is created in the main() receiving the Gadget MetaObject information.

# CustomModel C++ model to match both Qt5 and Qt6
It was necessary to create a C++ model, the view does not ask for Headers.
# QML files
## CustomListView
Uses the GadgetHelper::generateModelRow() to generate randomic data for a single row.

The model has a new property **numberOfRows** to say how many rows must be generated.

```
  model: CustomModel {
      id: fuzzyModel
      numberOfRows: 15
    }
```

