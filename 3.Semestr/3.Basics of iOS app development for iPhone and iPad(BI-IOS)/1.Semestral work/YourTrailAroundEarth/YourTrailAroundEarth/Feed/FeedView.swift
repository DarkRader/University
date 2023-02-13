//
//  FeedView.swift
//  YourTrailAroundEarth
//
//  Created by DarkRader on 01.02.2023.
//

import SwiftUI

struct FeedView: View {
    
    @State private var showingAddScreen = false
    
    @FetchRequest private var posts: FetchedResults<CoreDataPost>
    
    @Environment(\.managedObjectContext) private var moc
    
    init() {
        _posts = FetchRequest<CoreDataPost>(
            sortDescriptors: [
                SortDescriptor(\.id)
            ]
        )
    }
    
    var body: some View {
        NavigationStack {
            ScrollView {
                LazyVGrid(columns: [GridItem()]) {
                    ForEach(posts) { post in
                        PostView(post: post)
                    }
//                    .onDelete(perform: deleteCoreDataPosts)
                }
            }
            .navigationTitle("Feed")
            .toolbar {
                ToolbarItem(placement: .navigationBarTrailing) {
                    Button {
                        showingAddScreen.toggle()
                    } label: {
                        Label("Add a new city", systemImage: "plus")
                    }
                }
            }
        }
        .sheet(isPresented: $showingAddScreen) {
            AddPostView()
        }
    }
    
    private static func loadGamesFromFileSystem() -> [Post] {
        let documentDirectory = FileManager.default.urls(
            for: .documentDirectory,
            in: .userDomainMask
        ).first
        let url = documentDirectory?.appendingPathExtension(PostSave.url)
        
        guard let url = url else { return [] }
        
        do {
            let postsData = try Data(contentsOf: url)
            
            do {
                let posts = try JSONDecoder().decode([Post].self, from: postsData)
                return posts
            } catch {
                print("POSTS DECODING ERROR:", error.localizedDescription)
            }
        } catch {
            print("POSTS LOADING ERROR:", error.localizedDescription)
        }
        
        return []
    }
    
    private static func loadGamesFromUserDefaults() -> [Post] {
        guard
            let postsData = UserDefaults.standard.data(forKey: PostSave.userDefaultsKey)
        else { return [] }
        
        do {
            let posts = try JSONDecoder().decode([Post].self, from: postsData)
            return posts
        } catch {
            print("POSTS DECODING ERROR:", error.localizedDescription)
        }
        
        return []
    }
    
    private func deleteCoreDataPosts(at offsets: IndexSet) {
        for offset in offsets {
            let post = posts[offset]
            moc.delete(post)
        }
        
        try? moc.save()
    }
    
}

struct FeedView_Previews: PreviewProvider {
    static var previews: some View {
        FeedView()
    }
}
