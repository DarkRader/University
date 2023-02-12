//
//  PlaceWantToVisitView.swift
//  YourTrailAroundEarth
//
//  Created by DarkRader on 03.02.2023.
//

import SwiftUI

struct PlaceWantToVisitView: View {
    
    @State private var showingAddScreen = false
    
    @State var showError = false
    
    @FetchRequest private var places: FetchedResults<CoreDataPlaceWant>
    
    @Environment(\.managedObjectContext) private var moc
    
    init() {
        _places = FetchRequest<CoreDataPlaceWant>(
            sortDescriptors: [
                SortDescriptor(\.name)
            ]
        )
    }
    
    var body: some View {
        NavigationStack {
            List {
                ForEach(places) { place in
                    VStack(alignment: .leading) {
                        HStack {
                            Text(place.flag ?? "")
                            Text(place.country ?? "")
                        }
                        
                        Text("City: \(place.city ?? "")")
                                                
                        if place.type == "address" {
                            Text("Street: \(place.street ?? "")")
                                .fontWeight(.medium)
                            Text("Number of the street: \(place.number ?? "")")
                                .fontWeight(.medium)
                            Text("Postal code: \(place.postal_code ?? "")")
                                .fontWeight(.medium)
                        } else {
                            Text("Venue: \(place.name ?? "")")
                                .fontWeight(.medium)
                        }
                        
                    }
                }
                .onDelete(perform: deleteCoreDataWantPlaces)
            }
            .navigationTitle("Places desired to visit")
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
            AddPlaceWantToVisitView(showError: $showError)
        }
        .alert(isPresented: $showError) {
            Alert(title: Text("Error"), message: Text("This is not a place or not exist. Check the place that you wrote"), dismissButton: .default(Text("OK")))
        }
    }
    
    private static func loadCountriesFromFileSystem() -> [PlaceWantToVisit] {
        let documentDirectory = FileManager.default.urls(
            for: .documentDirectory,
            in: .userDomainMask
        ).first
        let url = documentDirectory?.appendingPathExtension(PlaceWantSave.url)
        
        guard let url = url else { return [] }
        
        do {
            let placesData = try Data(contentsOf: url)
            
            do {
                let places = try JSONDecoder().decode([PlaceWantToVisit].self, from: placesData)
                return places
            } catch {
                print("PLACES DECODING ERROR:", error.localizedDescription)
            }
        } catch {
            print("PLACES LOADING ERROR:", error.localizedDescription)
        }
        
        return []
    }
    
    private static func loadCountriesFromUserDefaults() -> [PlaceWantToVisit] {
        guard
            let placesData = UserDefaults.standard.data(forKey: PlaceWantSave.userDefaultsKey)
        else { return [] }
        
        do {
            let places = try JSONDecoder().decode([PlaceWantToVisit].self, from: placesData)
            return places
        } catch {
            print("PLACES DECODING ERROR:", error.localizedDescription)
        }
        
        return []
    }
    
    private func deleteCoreDataWantPlaces(at offsets: IndexSet) {
        for offset in offsets {
            let place = places[offset]
            moc.delete(place)
        }
        
        try? moc.save()
    }
}

struct PlaceWantToVisitView_Previews: PreviewProvider {
    static var previews: some View {
        PlaceWantToVisitView()
    }
}
