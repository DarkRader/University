//
//  AddNewGameView.swift
//  GamesApp
//
//  Created by DarkRader on 30.11.2022.
//

import SwiftUI

struct AddNewGameView: View {
    
    let genres = ["Sandbox", "MMORPG", "Simulator", "Sports"]
    @State private var title = ""
    @State private var genre = "Sandbox"
    @State private var review = ""
    @State private var rating = ""
    
    
    var body: some View {
        NavigationView {
            Form {
                Section("Basic information") {
                    TextField(
                        "Name of the game",
                        text: $title
                    )
                    
                    Picker("Genre", selection: $genre) {
                        ForEach(genres, id: \.self) {
                            Text($0)
                        }
                    }
                }
                
                Section("My review") {
                    TextEditor(text: $review)
                    
                    Picker
                }
            }
        }
    }
}

struct AddNewGameView_Previews: PreviewProvider {
    static var previews: some View {
        AddNewGameView(games: .constant([]))
    }
}
