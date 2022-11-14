//
//  CommentsScreenState.swift
//  Fitstagram
//
//  Created by DarkRader on 09.11.2022.
//

import Foundation

enum CommentsScreenState {
    case loading
    case error(Error)
    case comments([Comment])
}
