//
//  PostsView.swift
//  Fitstagram
//
//  Created by DarkRader on 19.10.2022.
//

import SwiftUI

//{
//    "postedAt" : "2022-04-15T08:46:01Z",
//    "text" : "đ¤",
//    "id" : "E7574AAB-2E6F-43EE-A803-1234953DC36A",
//    "photos" : [
//        "https:\/\/fitstagram.ackee.cz:443\/images\/176C9C71-9FB9-47C8-BE0C-27C9700E3A5C.jpg"
//    ],
//    "likes" : [
//
//    ],
//    "numberOfComments" : 0,
//    "author" : {
//        "username" : "zatim_bez_nazvu",
//        "id" : "C455A70A-A20F-4CAB-8940-F260AFB2F4C6"
//    }
//}

struct PostsView: View {
    @State var posts: [Post] = []
    
    @State var path = NavigationPath()
    
    @State private var showingAddScreen = false
    
    var body: some View {
        NavigationStack(path: $path) {
            Group {
                if posts.isEmpty {
                    ProgressView()
                        .progressViewStyle(.circular)
                        .task {
                            await fetchPosts()
                        }
                } else {
                    //buttonForAddPost()
                    ScrollView {
                        LazyVGrid(columns: [GridItem()]) {
                            ForEach(posts) { post in
                                PostView(
                                    post: post,
                                onCommentsButtonTap: {
                                    path.append(post)
                                }
                            )
                                    .onTapGesture {
                                        path.append(post)
                                    }
                            }
                        }
                    }
                }
            }
            
            .navigationDestination(for: Post.self) { post in
                PostDetailView(viewModel: PostDetailViewModel(postID: post.id))
            }
            .navigationTitle("FITstagram")
            .navigationBarTitleDisplayMode(.inline)
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
            AddNewPostView()
        }
    }
    
    private func fetchPosts() async {
        var request = URLRequest(url: URL(string: "https://fitstagram.ackee.cz/api/feed/")!)
        request.httpMethod = "GET"
        
        do {
            let (data, _) = try await URLSession.shared.data(for: request)
            self.posts = try JSONDecoder().decode([Post].self, from: data)
        } catch {
            print("[ERROR]", error)
        }
    }
}

struct SwiftUIView_Previews: PreviewProvider {
    static var previews: some View {
        PostsView()
    }
}
