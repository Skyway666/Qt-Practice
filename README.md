# 2D Engine

By Lucas García and Adriá Ferrer.

## Project Features

This 2D engine is basically a shape editor.

Start by creating your first object! You can do this by either selecting a shape and click "Add" on the hierarchy menu

![](https://github.com/Skyway666/Qt-Practice/blob/master/Web%20Images/Add_Hierarchy.PNG) 

Or directly click on the toolbar

![](https://github.com/Skyway666/Qt-Practice/blob/master/Web%20Images/Add_Toolbar.PNG)

Once an object is created, there is a list of attributes that can be edited, reflected in the inspector

- Name: Name which will represent the object in the hierarchy
- Active: Weather the object is to be drawn or not
- Shape: Which shape the object is
- Position: Top Left position of the object
- Scale: Ratio of width and height of the object
- Size: Scale of the object

- Fill color: Color picker!
- Stroke color: Color picker!
- Stroke thickness
- Stroke style: Solid, Dash or Dot

![](https://github.com/Skyway666/Qt-Practice/blob/master/Web%20Images/Inspector.PNG)

Feel free to remove any shape by selecting it on the hierarchy and clicking "remove". 

![](https://github.com/Skyway666/Qt-Practice/blob/master/Web%20Images/Remove.PNG)

If you mess up at any moment, you can click "back" or "forward" in the toolbar to do or undo your actions, as well
as in the main menu "Edit" or ctrl+z (undo) ctrl+y (redo)

![](https://github.com/Skyway666/Qt-Practice/blob/master/Web%20Images/Undo_Redo_Toolbar.PNG)![](https://github.com/Skyway666/Qt-Practice/blob/master/Web%20Images/Undo_Redo_MainMenu.PNG)

Once your scene is full of beautifull shapes, you can save your project by using the toolbar or the main menu "file",
and open it again in the same way. 

![](https://github.com/Skyway666/Qt-Practice/blob/master/Web%20Images/Save_Load_Toolbar.PNG)![](https://github.com/Skyway666/Qt-Practice/blob/master/Web%20Images/Save_Load_MainMenu.PNG)

If you are not working in any existing project and haven't started a new one, the save button will ask you to set a file 
to save to, otherwise it will automatically overwrite it.

![](https://github.com/Skyway666/Qt-Practice/blob/master/Web%20Images/New_File_Toolbar.PNG)

You can exit the app from the main menu.


## Examples

In the folder called "Project Examples", you can find two files which can be loaded in the engine, to be able to see 
the posibilities of the engine.

## Qt Features


Signals/Slots:

- Ui callbacks
- Communication UI pannels:
	- Hierarchy-Inspector.
	- Hierarchy-MainWindow.
	- Inspector-MainWindow.
		
		
Form files:

- The inspector is formed by a "universals", "shaperenderer" and "transform" form files.
- The main window is completelly composed by a form file.
- The hierarchy is another form file.

Style sheets:

- The color picker buttons were implementing using a style sheet.

	
Actions: 

- "New Project", "Open Project", "Save Project", "Undo", "Redo",
  "New Rectangle", "New Elipsis" and "Exit" are all actions.
	  
Parsing JSON:

- QFile, QJsonObject, QJsonArray, QJsonDocument and QByteArray are used for serialization.
	
Resource Files:

- All icons come from a resources file
	
Dialogs:

- When looking for a file to open or to save, a QFileDialog is used.
- When opening a project, the editor displays a QMessageBox::information with its path.
- When saving a project without having started one, the editor displays a QMessageBox::information with its path.
- When trying to "Remove" without selecting an object, a  QMessageBox::information 
  will be displayed with a warning.




# Links

Github Repo: https://github.com/Skyway666/Qt-Practice


