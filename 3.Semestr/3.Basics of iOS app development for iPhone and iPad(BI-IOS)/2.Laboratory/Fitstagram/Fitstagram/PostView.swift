//
//  PostView.swift
//  Fitstagram
//
//  Created by DarkRader on 12.10.2022.
//

import SwiftUI

struct PostView: View {
    let post: Post
    let onCommentsButtonTap: () -> Void

    var body: some View {
        VStack (alignment: .leading){
            HStack {
                Text(post.author.username)
                    .font(.callout)
                    .fontWeight(.semibold)

                Spacer()

                Button(action: { }) {
                    Image(systemName: "ellipsis")
                }
            }
            .padding(.horizontal, 8)

            Group {
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
            .frame(height: 400)
            .aspectRatio(contentMode: .fit)

            HStack(spacing: 16) {
                Button(action: { }) {
                    systemImage("heart")
                }

                Button(action: { }) {
                    systemImage("message")
                }

                Button(action: { }) {
                    systemImage("paperplane")
                }

                Spacer()

                Button(action: { }) {
                    systemImage("bookmark")
                }
            }
            .padding(.horizontal, 8)

            Text("\(post.likes) likes")
                .fontWeight(.semibold)
                .padding(.horizontal, 8)

            Group {
                Text(post.author.username)
                    .fontWeight(.semibold)
                +
                Text(" " + post.description)
            }
            .padding(.horizontal, 8)

            Button(action: {
                onCommentsButtonTap()
            }) {
                Text("View all comments (\(post.comments))")
            }
            .padding(8)
            .foregroundColor(.gray)
        }
    }

    private func systemImage(_ systemName: String) -> some View {
        Image(systemName: systemName)
            .resizable()
            .aspectRatio(contentMode: .fit)
            .frame(height: 24)
    }
}

struct PostView_Previews: PreviewProvider {
    static var previews: some View {
        PostView(
            post: Post(
                id: "1",
                likes: 1024,
                photos: [],
                description: "Top notch!",
                comments: 256,
                author: Author(id: "1", username: "Artem Kuznetsov", avatar: nil)
            ),
            onCommentsButtonTap: { }
        )
    }
}
