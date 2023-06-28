Sure, here is the README.md file for the smart_house console application:


# Smart House Console Application

This application allows you to control a smart house using a console.

## Commands

The following commands are available:

* `close` - Close the door. This command can be used by the `user`.
* `create` - Create a new object. This command can be used by the `user`.
* `delete` - Delete an existing object. This command can be used by the `user`.
* `demo` - Replace object schema with demo one. This command can be used by the `user`.
* `exit` - Terminate the program. This command can be used by any user.
* `help` - Display a list of available commands or a description of the specified command. This command can be used by any user.
* `list` - Display a list of objects or object properties. This command can be used by any user.
* `load` - Load the location of objects from the specified file. This command can be used by the `user`.
* `music` - Music playback control. This command can be used by the `user`.
* `musicposition` - Find out or set the current music playback position. This command can be used by the `user`.
* `off` - Turn off the lamp. This command can be used by the `user`.
* `on` - Turn on the lamp. This command can be used by the `user`.
* `open` - Open the door. This command can be used by the `user`.
* `store` - Save the location of the objects to the specified file. This command can be used by the `user`.
* `volume` - Find out or set the playback volume level. This command can be used by the `user`.

## Who can use which commands?

The following table shows which commands can be used by which users:

| Command | user |
|---|---|
| close | user |
| create | user |
| delete | user |
| demo | user |
| exit | user |
| help | user |
| list | user |
| load | user |
| music | user |
| musicposition | user |
| off | user |
| on | user |
| open | user |
| store | user |
| volume | user |

## Example

The following example shows how to use the application to close the door, list all objects, and then open the door:


close
list
open
```

This would close the door, list all objects in the smart house, and then open the door.

## Notes

* The application must be run from the directory where it is located.
* The application requires the following libraries:
    * ncurses
    * libyaml

## Building the Application

To build the application, you can use the following command:

```
make
```

This will create an executable file named `smart_house`.

## Running the Application

To run the application, you can use the following command:

```
./smart_house
```

This will start the application and wait for you to enter commands.
```

Do you have other questions or requests? Let me know.