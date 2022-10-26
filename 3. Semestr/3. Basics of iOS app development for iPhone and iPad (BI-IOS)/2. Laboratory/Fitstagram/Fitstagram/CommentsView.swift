//
//  CommentsView.swift
//  Fitstagram
//
//  Created by Артем on 19.10.2022.
//

import SwiftUI

struct CommentsView: View {
    @State var comment = [
       Comment(username: "DarkRader", text: "Nice!"),
       Comment(username: "kuznear1", text: "Nice!"),
       Comment(username: "Vlastilin", text: "🎃"),
       Comment(username: "raghzon", text: "dwadwa"),
       ]
    
    @State var sheetPresented = false
    
    var body: some View {
        List {
            ForEach(comment) { comment in
                HStack {
                    Text(comment.username)
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
            NewCommentView(
                isPresented: $sheetPresented,
                 onNewComment: {
                    comment.append(Comment(username: "new.comment.guy", text: $0))
                }
            )
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
        CommentsView()
    }
}
