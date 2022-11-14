//
//  InformationPost.swift
//  Fitstagram
//
//  Created by DarkRader on 14.11.2022.
//

import SwiftUI

struct InformationPost: View {
    let post: Post
    @State var posts: [Post] = []
    
    @State var path = NavigationPath()
    
    let randomInt = Int.random(in: 1..<10)
    
    var body: some View {
        
        VStack (alignment: .leading) {
            HStack {
                Circle()
                    .frame(width: 32, height: 32)
                Text(post.author.username)
                    .font(.callout)
                    .fontWeight(.semibold)
                Spacer()
            }
            .padding(.horizontal, 8)
            
            if posts.isEmpty {
                ProgressView()
                    .progressViewStyle(.circular)
                    .task {
                        await fetchInfPost()
                    }
            } else {
                TabView {
                    ForEach(0...randomInt, id: \.self) {_ in
                    if let image = post.photos.first {
                        AsyncImage(url: URL(string: image)) {
                            $0.resizable()
                        } placeholder: {
                            ProgressView()
                                .progressViewStyle(.circular)
                        }
                    } else {
                        Image("nature")
                            .resizable()
                    }
                }
            }
            .tabViewStyle(.page(indexDisplayMode: .always))
            .indexViewStyle(.page(backgroundDisplayMode: .always))
            }
            
            HStack {
                Text("\(post.comments) comments:")
                    .padding(8)
                    .foregroundColor(.gray)
                Spacer()
            }
            .padding(.horizontal, 8)
            CommentsView(viewModel: .init(postID: post.id))
        }
//        CommentsView(viewModel: .init(postID: post.id))
    }
    
    private func fetchInfPost() async {
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

struct InformationPost_Previews: PreviewProvider {
    static var previews: some View {
        InformationPost(
            post: Post(
                id: "1",
                likes: 1024,
                photos: [],
                description: "Top notch!",
                comments: 256,
                author: Author(id: "1", username: "Artem Kuznetsov")
            )
        )
    }
}
