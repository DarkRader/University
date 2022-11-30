//
//  ContentView.swift
//  GamesApp
//
//  Created by DarkRader on 30.11.2022.
//

import SwiftUI

struct ContentView: View {
    
    @State var games: [Game] = []
    @State private var showingAddScreen = false
    
    init(games: [Game]) {
        self.games = Self.loadGamesFromFileSystem()
    }
    
    var body: some View {
        NavigationView {
            List {
                ForEach(games) { game in
                    HStack {
                        VStack(alignment: .leading) {
                            Text(game.title)
                                .fontWeight(.heavy)
                            
                            Text("Genre: \(game.genre)")
                                .fontWeight(.medium)
                        }
                        
                        Spacer()
                        
                        Text(String(game.rating))
                    }
                }
            }
            .navigationTitle("Games List")
            .toolbar {
                ToolbarItem(placement: .navigationBarTrailing) {
                    Button {
                        showingAddScreen.toggle()
                    } label: {
                        Label("Add a new game", systemImage: "plus")
                    }
                }
            }
        }
        .sheet(isPresented: $showingAddScreen) {
            AddNewGameView(games: $games)
        }
    }
    
    private static func loadGamesFromFileSystem() -> [Game] {
        let documentDirectory = FileManager.default.urls(
            
        )
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView(games: [])
    }
}
