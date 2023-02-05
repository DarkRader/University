//
//  ContentView.swift
//  YourTrailAroundEarth
//
//  Created by DarkRader on 01.02.2023.
//

import SwiftUI

struct ContentView: View {
    var body: some View {
        TabView {
            FeedView()
                .tabItem {
                    Label("Feed", systemImage: "list.dash")
                }
            MyVisetedPlaceView(
            keyName: "title", letter: "S"
            )
                .tabItem {
                    Label("Visited place", systemImage: "checklist")
                }
            WantToVisiteView()
                .tabItem {
                    Label("Want to visite", systemImage: "heart.fill")
                }
            ProfileView()
                .tabItem {
                    Label("Profile", systemImage: "person")
                }
        }
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
            .preferredColorScheme(.light)
        ContentView()
            .preferredColorScheme(.dark)
    }
}
