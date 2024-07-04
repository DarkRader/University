# BI-IOS 2022

| Lecture | Lecturer | Stanford |
| --------- | -------- | -------- |
| 01 Xcode, Swift Basics | LH | [Swift](https://cs193p.sites.stanford.edu/sites/g/files/sbiybj16636/files/media/file/reading_1.pdf) |
| 02 SwiftUI Basics | LH | [Getting Started with SwiftUI](https://www.youtube.com/watch?v=bqu6BquVi2M) |
| 03 More SwiftUI | IR | [Getting Started with SwiftUI](https://www.youtube.com/watch?v=bqu6BquVi2M) |
| 04 Navigace | IR | [Learning More about SwiftUI](https://youtu.be/3lahkdHEhW8) |
| 05 Networking, multithreading | LH | Not Available |
| 06 Async/await | LH | Not Available |
| 07 MVVM | IR | [MVVM](https://youtu.be/--qKOhdgJAs)<br>[More MVVM enum Optionals](https://youtu.be/oWZOFSYS5GE) |
| 08 MVVM + UIImagePicker | LH | [MVVM](https://youtu.be/--qKOhdgJAs)<br>[More MVVM enum Optionals](https://youtu.be/oWZOFSYS5GE) |
| 09 Environment | LH | Not Available |
| 10 Persistence | IR  | [Persistence](https://youtu.be/pT5yiBu2xbU)<br>[More Persistence (Core Data, CloudKit)](https://youtu.be/wX3ruVLlWPg) |
| 11 Push notifications | IR  | Not Available |

Throughout the course, we recommend watching the online lectures from Stanford, which serve as the main source of information for this course [https://cs193p.sites.stanford.edu](https://cs193p.sites.stanford.edu).

## 1. Assignment

> :exclamation: Deadline: **15. 11. 2022 23:59:59**

> The complete API documentation is [here](https://fitstagram.ackee.cz/docs/)

Your task is to create a post detail view..

The detail view will contain all the photos that are uploaded with the post – there can be more than one photo. How you display them is up to you, but it might be helpful to google how to create a `pageView` in SwiftUI. :bulb: :smirk:

The detail view should also display the author’s username and include the comments on the post in an appealing way – everything will be displayed on one screen.

To load comments, use the following URL:
```
https://fitstagram.ackee.cz/api/feed/{postID}/comments
```
where `{postID}` is the ID of the post from the Feed. We talked in the lecture about how not to block the main thread, try to follow that. :pray:

Try to combine all these elements on one screen nicely.

You can submit your work via email to `lukas.hromadnik@ackee.cz` or invite me to your repo where you have the solution, and email me the branch/commit where I can find the solution.

**Bonus** (max 2 body): Add a button or some other action on the screen that hides/displays all other information except the photos. That means performing an action to hide everything except the photos and another action to display the information back. We do not want to display a new screen with only photos but modify the existing screen.

## 2. Assignment

> :exclamation: Deadline: **13. 12. 2022 23:59:59**

Your second task is to create a screen and complete logic for adding a new post.

Each new post will contain a selected photo and a caption. Both parameters are required.

The UI for creating a post is in your hands. Connect the new screen to the “+” button on the main page.

The basic flow for adding a post should be as follows:

1.	Tap the “+” button and display the screen for adding a new post.
2.	On this screen, select an image from the gallery (or maybe even from the camera, optional), which will then be displayed.
3.	Add a caption to the image using a text field.
4.	By tapping another button, a request to the API is constructed and the data is sent.
5.	If an error is returned from the server, display it.
6.	After successfully creating and sending the post, redirect back to the list.
7.	In the list, have the ability to scroll to the new post.

To create a post, use this [endpoint](https://fitstagram.ackee.cz/docs/#/Feed/post_feed).

Photos need to be modified before sending to the server.

1.	Neither the width nor the height of the photo can exceed 2048 pixels. So you may need to resize the image.
2.	Send photos to the server as JPEG encoded in a base64 string.

We didn’t show both of these operations in the lectures, but a simple Google search will get you the answers. If you can’t manage, we will provide you with the code to do it. We intentionally don’t want to give it to you at the beginning so you can try it yourself. It really isn’t that hard.

## Semester Work

For the semester project, your task is to demonstrate what you have learned. The topic is up to you, but it needs my approval. Approval must be obtained by the end of the lecture period, i.e., by the last lecture.

You then have the entire semester to work on it – until the end of the exam period.

If the situation allows, the submission will take place in person [at our offices](https://mapy.cz/zakladni?source=firm&id=12749992&ds=1&x=14.3907423&y=50.0997880&z=17). Do not leave the submission to the last minute to ensure you have a time slot. If you leave the submission to the last day, it may be impossible to find a submission time, and therefore complete the course.

If the situation does not allow, the submission will be online.

The scope of the project should be 3-5 screens (can be fewer if it makes sense within the assignment) using the MVVM architecture. Ideally, show more interesting things than just static screens – networking, multithreading, gestures, map, image selection, drawing, etc.

## Lectures

### 01 Xcode, Swift Basics
* Xcode
* Swift
    * `String`, `Int`, `Bool`, `Double`
    * podmínky, cykly
    * `Optional`
    * Pole, dictionaries, tuples
    * `struct`, `enum`, `class`
    * Protokoly, extensions

### 02 SwiftUI Basics
* Swift
    * Access control
    * Trailing closure syntax
* SwiftUI
    * `View`, `some`, `@ViewBuilder`
    * `VStack`, `HStack`, `Text`, `Button`, `Image`
    * SFSymbols

### 03 More SwiftUI
* Sizing (top-down, bottom-up)
* View modifiers
* `LazyVGrid`/`LazyHGrid`
* `ForEach`
* `ScrollView`
* Protocols
    * `Equatable`
    * `Hashable`
    * `Identifiable`
    * `Comparable`

### 04 Navigation
* Human Interface Guidelines
* Xcode shortcuts
* `List`
* Property wrappers
* `@State`, `@Binding`, `@Environment`
* View presentation
    * Alert
    * Sheet
    * `fullScreenCover`
* `NavigationStack`, `NavigationLink`, `NavigationPath`
* `TabView`

### 05 Networking
* Closures
* REST, API
* Request
* `URLSession.shared.dataTask`

### 06 Async/Await
* `Codable`
    * `CodingKeys`
    * `init(from decoder: Dedocer)`
    * `encode(to encoder: Encoder)`
    * zanořené objekty
* Async/await
    * `Task`
    * `@MainActor`
    * func async

### 07 MVVM
* MVVM architecture
* `ObservableObject`, `ObservedObject`/`StateObject`, `@Published`
* Value types vs. reference types
* `enum` associated values
* Error handling and debugging basics

### 10 Persistence
* File system, `FileManager`
* `UserDefaults`
* `Core Data`
* `CloudKit`

### 11 Push notifications
* Code signing, APNS key
* Push notifications
* Notification Service Extension
* iMessage Extension
* SwiftUI <-> UIKit interfacing
