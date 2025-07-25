//
//  CommentsView.swift
//  Fitstagram
//
//  Created by DarkRader on 19.10.2022.
//

import SwiftUI
    
struct CommentsView: View {
    @StateObject var viewModel: CommentsViewModel
    
    var body: some View {
        CommentsContentView(
            state: viewModel.state,
            onNewComment: { viewModel.isNewCommentPresented = true }
        )
        .refreshable {
            await viewModel.fetchComments()
        }
        .task {
            await viewModel.fetchComments()
        }
        .sheet(isPresented: $viewModel.isNewCommentPresented) {
            NewCommentView(
                viewModel: NewCommentViewModel(
                    postID: viewModel.postID,
                    isPresented: $viewModel.isNewCommentPresented,
                    onNewComment: { _ in
                        Task {
                            await viewModel.fetchComments()
                        }
                    }
                )
            )
        }
//        .sheet(isPresented: $sheetPresented) {
//            NewCommentView(
//                isPresented: $sheetPresented,
//                 onNewComment: {
//                    comment.append(Comment(username: "new.comment.guy", text: $0))
//                }
//            )
//        }
//        .alert(isPresented: $alertDispayed) {
//            Alert(
//                title: Text("This is my alert!"),
//                message: Text("Messange of alert!"),
//                primaryButton: .destructive(Text("Desctructive"), action: {}),
//                secondaryButton: .default(Text("Got it!"), action: {})
//                )
//        .alert(
//        "Login",
//        isPresented: $alertDispayed,
//        actions: {
//            TextField("Username", text: .constant(""))
//            SecureField("Password", text: .constant(""))
//
//            Button("Login", action: {})
//            Button("Cancel", role: .cancel, action: {})
//        }, message: {
//            Text("Please enter your username and password.")
//        }
//        )
    }
}

struct CommentsView_Previews: PreviewProvider {
    static var previews: some View {
        CommentsView(viewModel: .init(postID: "1"))
    }
}
