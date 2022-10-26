//
//  PostsView.swift
//  Fitstagram
//
//  Created by Артем on 19.10.2022.
//

import SwiftUI

struct PostsView: View {
    var posts = [
        Post(username: "Artem Kuznetsov", likes: 1240, description: "Top notch!", comments: 256),
        Post(username: "Maks Garbunov", likes: 4234, description: "Good view!", comments: 2553),
        Post(username: "Gray Black", likes: 342, description: "Something cool!", comments: 35),
    ]
    
    @State var path = NavigationPath()
    
    var body: some View {
        NavigationStack(path: $path) {
            ScrollView {
                LazyVGrid(columns: [GridItem()]) {
                    ForEach(posts) { post in
                        PostView(post: post)
                            .onTapGesture {
                                path.append(post)
                            }
                    }
                }
            }
            .navigationDestination(for: String.self) { string in
                Text(string)
            }
            .navigationDestination(for: Int.self) { integer in
                Text("\(integer)")
            }
            .navigationDestination(for: Post.self) { post in
                VStack {
                    Text(post.username)
                    
                    Text("\(post.comments)")
                    
                    Button("PUSH FIRST POST") {
                        path.append(posts[0])
                    }
                    
                    Button("POP TO ROOT") {
                        path.removeLast(path.count)
                    }
                }
            }
            .navigationTitle("FITstagram")
        }
    }
}

struct PostsView_Previews: PreviewProvider {
    static var previews: some View {
        PostsView()
    }
}
