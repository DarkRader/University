import SwiftUI

@main
struct Cviko12App: App {
    var body: some Scene {
        WindowGroup {
            TabView {
                AuthenticationView()
                    .tabItem {
                        Label("Authenticatoion", systemImage: "faceid")
                    }

                TableView()
                    .tabItem {
                        Label("Preferences", systemImage: "square.grid.3x2")
                    }
            }
        }
    }
}
