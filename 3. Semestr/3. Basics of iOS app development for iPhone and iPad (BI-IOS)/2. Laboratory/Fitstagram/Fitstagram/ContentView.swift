//
//  ContentView.swift
//  Fitstagram
//
//  Created by Артем on 12.10.2022.
//

import SwiftUI

struct ContentView: View {
    
    var body: some View {
        TabView {
            PostsView()
                .tabItem {
                    Label("Feed", systemImage: "list.dash")
                }
            
            CommentsView()
                .tabItem {
                    Label("Comments", systemImage: "person")
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
