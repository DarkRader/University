import { Injectable } from '@angular/core';
import { Router } from '@angular/router';
import { Subject } from 'rxjs';
import { ApiService } from './api.service';
import { ApiUserData } from 'src/app/objects/api-user-data';
import { UserData } from 'src/app/objects/user-data';

@Injectable({
  providedIn: 'root'
})
export class UsermapService {

  private userDataSubject = new Subject<UserData>();
  userData$ = this.userDataSubject.asObservable();

  constructor(private apiService: ApiService, private router: Router) { }

  getUserData(){
    return this.apiService.getUserInfo().subscribe({

      next :(apiUserData: ApiUserData) => {
        const userData: UserData = {
          username: apiUserData.username,
          firstName: apiUserData.first_name,
          lastName: apiUserData.last_name,
          email: apiUserData.email,
          uuid: apiUserData.uuid,
          dsrToken: apiUserData.dsr_token
        };
        localStorage.setItem('dsr_token', apiUserData.dsr_token);
        console.log(userData)
        this.userDataSubject.next(userData);
      },

      error: (err) => {
        this.router.navigate(['/'])
      }
      
     })
  }
}
