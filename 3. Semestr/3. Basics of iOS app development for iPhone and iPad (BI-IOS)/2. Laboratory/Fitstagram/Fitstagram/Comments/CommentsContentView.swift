//
//  CommentsContentView.swift
//  Fitstagram
//
//  Created by DarkRader on 09.11.2022.
//

import SwiftUI

struct CommentsContentView: View {
    
    let state: CommentsScreenState
    @State var sheetPresented = false
    
    var body: some View {
        switch state {
        case .loading:
            ProgressView()
        case .error(let error):
            Text(error.localizedDescription)
                .foregroundStyle(.red)
        case .comments(let comments):
            List {
                ForEach(comments) { comment in
                    HStack {
                        Text(comment.author.username)
                            .fontWeight(.semibold)
                        
                        Text(comment.text)
                    }
                }
                
                Button(action: {
                    sheetPresented = true
                }) {
                    Image(systemName: "plus")
                    
                }
            }
            .listStyle(.grouped)
            .sheet(isPresented: $sheetPresented) {
                NewCommentView(
                    isPresented: $sheetPresented,
                    onNewComment: { _ in
                        //TODO: Handle 'onNewComment'
                    }
                )
            }
        }
    }
}

struct CommentsContentView_Previews: PreviewProvider {
    static var previews: some View {
        CommentsContentView(
            state: .comments(
                [
                .init(id: "1", author: .init(id: "1", username: "DarkRader"),
                      text: "❤️❤️❤️"),
                .init(id: "2", author: .init(id: "2", username: "artem_rader"),
                      text: "🏎🏎🏎"),
                .init(id: "3", author: .init(id: "3", username: "DarlingGather"),
                      text: "🤷‍♂️🤷‍♂️🤷‍♂️")
                ]
            )
        )
    }
}
