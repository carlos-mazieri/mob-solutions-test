This is the C++ application.
Many Constructors and Destructors contain **qDebug()** to check their allocation/deallocation.  

Both **Player** and **P2D** contain **qDebug()** on their WRITE operations.  

For debbuging purposes, **Player** initializes **"struct items"** with random values, this initialization depends on the _INIT_COORDINATE_VALUES_ define.
## Main classes
### Player
  This is the main Q_GADGET, it manages its **"struct items"** allocation/deallocation.
### P2D
  This is the **"struct items"** Q_GADGET items, the **Player** may have many instances of it.
## FrameGrided
   Provides a QFrame with QGridLayout as ***container***  for all items editors.
   This class keeps ownership from all items editors.
## GadgetEditor
   It is an abstract class to edit all different types of items.
   Each editable property from a Gadget object will have sub class of GadgetEditor assigned to each.
   The **editor()** method returns the widget suitable for each property.
   Sub classes are responsible to write the data from editor() into the gadget.
   Both **label()** and **editor()** widgets are put together on a **FrameGrided** ***container*** widget.  
### Sub classes:
   - GadgetEditorBoolean
   - GadgetEditorDouble
   - GadgetEditorEnumerator
   - GadgetEditorInteger
   - GadgetEditorStruct  for other Q_GADGET grouped item as property of the main Q_GADGET.
### GadgetEditorStruct class
   On its method **editor()** it returns a ***container*** (_FrameGrided_) to receive all objects, each object will be a group.   
## GadgetEditorFactory 
  This is the main class of the Editor.
### Responsibilities:
   - Parses the Meta Objects to create all Editors (sub classes of **GadgetEditor** class)
   - Handles the adding/removing of "struct items" editors and ***containers***.
   
   For each **"struct item"** Q_GADGET instance it creates a child ***container***  of the  ***container*** created by **GadgetEditorStruct** object.
    
