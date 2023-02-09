//
//  MyVisitedPlaceView.swift
//  YourTrailAroundEarth
//
//  Created by DarkRader on 09.02.2023.
//

import SwiftUI

struct MyVisitedPlaceView: View {
    
    @State private var showingAddScreen = false
    
    @State private var showReview = false
    
    @FetchRequest private var placies: FetchedResults<CoreDataPlace>
    
    @Environment(\.managedObjectContext) private var moc
    
    private var keyName: String
    
    private var letter: String
    
    private var city: CoreDataCity
    
    init(keyName: String, letter: String, city: CoreDataCity) {
        self.keyName = keyName
        self.letter = letter
        self.city = city
        
        _placies = FetchRequest<CoreDataPlace>(
            sortDescriptors: [
                SortDescriptor(\.rating, order: .reverse),
                SortDescriptor(\.name)
            ]

        )
    }
    
    var body: some View {
        NavigationStack {
            List {
                ForEach(city.placiesList, id: \.self) { place in
                    VStack(alignment: .leading) {
                        HStack {
                            Text(place.origin?.name ?? "")
                            Text(place.name ?? "")
                                .fontWeight(.heavy)
                            
                            Spacer()
                            
                            Button(action: {
                                deleteCoreDataPlacies(place: place)
                            }) {
                               Image(systemName: "trash")
                            }
                            .buttonStyle(BorderlessButtonStyle())
                        }
                        
                        Button("Show review:") {
                           showReview.toggle()
                        }
                        .buttonStyle(BorderlessButtonStyle())

                        if(showReview) {
                           Text(place.review ?? "")
                        }

                        Text("Rating: \(String(place.rating))")
                        
                    }
                }
//                .onDelete(perform: deleteCoreDataPlacies)
            }
            .navigationTitle("Visited placies")
            .toolbar(.hidden, for: .tabBar)
            .toolbar {
                ToolbarItem(placement: .navigationBarTrailing) {
                    Button {
                        showingAddScreen.toggle()
                    } label: {
                        Label("Add a new place", systemImage: "plus")
                    }
                }
            }
        }
        .sheet(isPresented: $showingAddScreen) {
            AddNewVisitedPlaceView(city: city)
        }
    }
    
    private static func loadCitiesFromFileSystem() -> [Place] {
        let documentDirectory = FileManager.default.urls(
            for: .documentDirectory,
            in: .userDomainMask
        ).first
        let url = documentDirectory?.appendingPathExtension(PlaceSave.url)
        
        guard let url = url else { return [] }
        
        do {
            let placiesData = try Data(contentsOf: url)
            
            do {
                let placies = try JSONDecoder().decode([Place].self, from: placiesData)
                return placies
            } catch {
                print("PLACIES DECODING ERROR:", error.localizedDescription)
            }
        } catch {
            print("PLACIES LOADING ERROR:", error.localizedDescription)
        }
        
        return []
    }
    
    private static func loadCitiesFromUserDefaults() -> [Place] {
        guard
            let placiesData = UserDefaults.standard.data(forKey: PlaceSave.userDefaultsKey)
        else { return [] }
        
        do {
            let placies = try JSONDecoder().decode([Place].self, from: placiesData)
            return placies
        } catch {
            print("PLACIES DECODING ERROR:", error.localizedDescription)
        }
        
        return []
    }
    private func deleteCoreDataPlacies(place: CoreDataPlace) {
        moc.delete(place)

        try? moc.save()
    }
}

struct MyVisitedPlaceView_Previews: PreviewProvider {
    static var previews: some View {
        MyVisitedPlaceView(keyName: "title", letter: "S", city: CoreDataCity())
    }
}
