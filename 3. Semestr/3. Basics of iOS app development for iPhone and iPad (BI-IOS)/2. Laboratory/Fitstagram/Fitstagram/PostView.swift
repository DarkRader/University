//
//  PostView.swift
//  Fitstagram
//
//  Created by Артем on 12.10.2022.
//

import SwiftUI

struct PostView: View {
    let post: Post
    
    var body: some View {
        VStack (alignment: .leading){
            HStack {
                Text(post.username)
                    .font(.callout)
                    .fontWeight(.semibold)
                
                Spacer()
                
                Button(action: { }) {
                    Image(systemName: "ellipsis")
                }
            }
            .padding(.horizontal, 8)
            
            Image("nature")
                .resizable()
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
            
            Text("\(post.likes) To se mi libi")
                .fontWeight(.semibold)
                .padding(.horizontal, 8)
            
            Group {
                Text(post.username)
                    .fontWeight(.semibold)
                +
                Text(" " + post.description)
            }
            .padding(.vertical, 4)
            .padding(.horizontal, 8)
            
            Button(action: { }) {
                Text("Zobrazit vsechni komentare (\(post.comments)")
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
                username: "Artem Kuznetsov",
                likes: 1024,
                description: "Top notch!",
                comments: 256
        ))
    }
}
