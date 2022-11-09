//
//  CommentsView.swift
//  Fitstagram
//
//  Created by Артем on 19.10.2022.
//

import SwiftUI

enum CommentsScreenState {
    case loading
    case error(Error)
    case comments([Comment])
    
//    var message: String {
//        switch self {
//        case .loading:
//            return "Loading.."
//        case .error(let error):
//            return error.localizedDescription
//        case .comments(let comments):
//            return comments.first?.text ?? ""
//        }
//    }
}

class CommentsViewModel: ObservableObject {
    @Published var comments: [Comment] = []
    @Published private(set) var state: CommentsScreenState = .loading
    
    private let postID: Post.ID
    
    init (postID: Post.ID) {
        self.postID = postID
    }
    
    @MainActor
    func fetchComments() async {
        var request = URLRequest(url: URL(string: "https://fitstagram.ackee.cz/api/feed/\(postID)/comments")!)
        request.httpMethod = "GET"
        request.timeoutInterval = 2
        
        do {
            let (data, _) = try await URLSession.shared.data(for: request)
            self.comments = try JSONDecoder().decode([Comment].self, from: data)
            state = .comments(comments)
        } catch {
            state = .error(error)
            print("[ERROR]", error)
        }
    }
}

struct CommentsContentView: View {
    
    let state: CommentsScreenState
    @State var sheetPresented = false
    
    var body: some View {
        switch state {
        case .loading:
            ProgressView()
        case .error(let error):
        case .comments(let array):
        }
        List {
            ForEach(viewModel.comments) { comment in
                HStack {
                    Text(comment.author.username)
                        .fontWeight(.semibold)
                    
                    Text(comment.text)
                }
            }
            Button(action: {
                //comment.append(Comment(username: "FunRader", text: "🤧"))
                sheetPresented = true
            }) {
                Image(systemName: "plus")
                
            }
        }
        .listStyle(.grouped)
        .sheet(isPresented: $sheetPresented) {

        }
}

struct CommentsView: View {
//    @State var comment = [
//       Comment(username: "DarkRader", text: "Nice!"),
//       Comment(username: "kuznear1", text: "Nice!"),
//       Comment(username: "Vlastilin", text: "🎃"),
//       Comment(username: "raghzon", text: "dwadwa"),
//       ]
    
    @StateObject var viewModel: CommentsViewModel
    
    @State var sheetPresented = false
    
    var body: some View {
        List {
            ForEach(viewModel.comments) { comment in
                HStack {
                    Text(comment.author.username)
                        .fontWeight(.semibold)
                    
                    Text(comment.text)
                }
            }
            Button(action: {
                //comment.append(Comment(username: "FunRader", text: "🤧"))
                sheetPresented = true
            }) {
                Image(systemName: "plus")
                
            }
        }
        .listStyle(.grouped)
        .task {
            await viewModel.fetchComments()
        }
        .sheet(isPresented: $sheetPresented) {
//            NewCommentView(
//                isPresented: $sheetPresented,
//                 onNewComment: {
//                    comment.append(Comment(username: "new.comment.guy", text: $0))
//                }
//            )
        }
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
