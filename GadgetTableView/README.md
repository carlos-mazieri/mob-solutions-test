Chosen solution was to create the QObject helper class **GadgetHelper**.

This object is created in the main() receiving the Gadget MetaObject information.

#QML files
##CustomModel
Uses the GadgetHelper::generateModelRow() to generate randomic data for a single row.

The model has a new property **numberOfRows** to say how many rows must be generated.

```
  model: CustomModel {
      id: fuzzyModel
      numberOfRows: 15
    }
```
##CustomListView
Uses the GadgetHelper::columnList() to create its set of **TableViewColumn** objects.
# The current solution does not for Qt6
QtQuick.Controls version 1.4 is not present in Qt6.

No other solution than creating  **CustomModel** as a C++ object was found, and, it was not the definition.

