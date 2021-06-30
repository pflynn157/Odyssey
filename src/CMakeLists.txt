cmake_minimum_required(VERSION 3.0.0)
project(odyssey)

set(DIALOGS_SRC
	dialogs/appchooserdialog.cpp
	dialogs/helpdialog.cpp
	dialogs/helpdialog.ui
	dialogs/keyboardshortcutsdialog.cpp
	dialogs/keyboardshortcutsdialog.ui
)

set(MENU_SRC
	menu/background_contextmenu.cpp
	menu/file_contextmenu.cpp
	menu/folder_contextmenu.cpp
	menu/multi_contextmenu.cpp
)

set(MENUBAR_SRC
	menubar/editmenu.cpp
	menubar/filemenu.cpp
	menubar/helpmenu.cpp
	menubar/viewmenu.cpp
)

set(BASE_SRC
	icons.qrc
	rsc.qrc
	actions.cpp
	addressbar_buttons.cpp
	addressbar_text.cpp
	browserwidget.cpp
	endtoolbar.cpp
	main.cpp
	navbar.cpp
	searchbar.cpp
	sidebar.cpp
	tabwidget.cpp
	tinyxml2.cpp
	trash.cpp
	trashbar.cpp
	window.cpp
)

set(SRC
	${DIALOGS_SRC}
	${MENU_SRC}
	${MENUBAR_SRC}
	${BASE_SRC}
)

add_executable(odyssey ${SRC})

target_link_libraries(odyssey
	Qt5::Core
	Qt5::Widgets
	Qt5::Gui
)

