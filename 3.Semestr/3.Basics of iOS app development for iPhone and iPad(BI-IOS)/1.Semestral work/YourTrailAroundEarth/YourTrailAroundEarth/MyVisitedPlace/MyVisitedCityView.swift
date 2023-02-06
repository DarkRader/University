//
//  MyVisitedCityView.swift
//  YourTrailAroundEarth
//
//  Created by DarkRader on 05.02.2023.
//

import SwiftUI

struct MyVisitedCityView: View {
    
    @State private var showingAddScreen = false
    
    var body: some View {
        NavigationView {
            List {
                
                
            }
            .navigationTitle("Visited cities")
            .toolbar {
                ToolbarItem(placement: .navigationBarTrailing) {
                    Button {
                        showingAddScreen.toggle()
                    } label: {
                        Label("Add a new city", systemImage: "plus")
                    }
                }
                
                ToolbarItem(placement: .navigationBarLeading) {
                    EditButton()
                }
            }
        }
        .sheet(isPresented: $showingAddScreen) {
            AddNewVisitedCityView()
        }
    }
}

struct MyVisitedCityView_Previews: PreviewProvider {
    static var previews: some View {
        MyVisitedCityView()
    }
}
