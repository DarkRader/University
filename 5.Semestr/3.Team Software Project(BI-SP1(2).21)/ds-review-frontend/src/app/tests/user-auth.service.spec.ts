import { TestBed, fakeAsync, inject, tick } from '@angular/core/testing';
import { UserAuthService } from 'src/app/services/user-auth.service';
import { of, throwError } from 'rxjs';
import { ApiService } from 'src/app/services/api.service';

describe('YourAuthService', () => {
  let authService: UserAuthService;
  let apiServiceSpy: jasmine.SpyObj<ApiService>;

  beforeEach(() => {
    apiServiceSpy = jasmine.createSpyObj('ApiService', ['postRegistration', 'postLogin']);

    TestBed.configureTestingModule({
      providers: [
        UserAuthService, 
        { provide: ApiService, useValue: apiServiceSpy }]
    });

    authService = TestBed.inject(UserAuthService);
  });

  it('should be created', () => {
    expect(authService).toBeTruthy();
  });
  
  it('should register a user successfully', fakeAsync(() => {
    // Arrange
    const firstName = 'John';
    const lastName = 'Doe';
    const username = 'john.doe';
    const password = 'password';
    const email = 'john.doe@example.com';
     
    apiServiceSpy.postRegistration.and.returnValue(of({ code: 200 }));
    // Act
    let result: Boolean | undefined;
    authService.registerUser(firstName, lastName, username, password, email)
      .then(res => result = res);
    tick();
  
    // Assert
    expect(result).toBe(true);
    expect(apiServiceSpy.postRegistration).toHaveBeenCalledWith(
      jasmine.objectContaining({
        username,
        last_name: lastName,
        first_name: firstName,
        email,
        password
      })
    );

  }));
  
  it('should handle registration failure', fakeAsync(() => {
    // Arrange
    const username = 'john.doe';
    const password = 'password';
  
    const expectedError = { status: 422, statusText: 'Validation Error' };
    apiServiceSpy.postRegistration.and.returnValue(throwError(()=>expectedError)); //line 59
  
    // Act
    let result: Boolean | undefined;
    authService.registerUser('', '', username, password, '')
      .then(res => result = res);
    tick();
  
    // Assert
    expect(result).toBe(false);
    expect(apiServiceSpy.postRegistration).toHaveBeenCalled();
  }));
  
  it('should return true on successful login', fakeAsync(() => {
    // Arrange
    const username = 'john.doe';
    const password = 'password';
    const accessToken = 'your_access_token';
  
    apiServiceSpy.postLogin.and.returnValue(of({ code:200, access_token: accessToken }));
  
    // Act
    let result: Boolean | undefined;
    authService.login(username, password)
      .then(res => result = res);
    tick();
  
    // Assert
    expect(result).toBe(true);
    expect(apiServiceSpy.postLogin).toHaveBeenCalledWith(
      `grant_type=&username=${encodeURIComponent(username)}&password=${encodeURIComponent(password)}&scope=&client_id=&client_secret=`
    );
    localStorage.removeItem('access_token');
  }));
  
  it('should store the access token on successful login', fakeAsync(() => {
    // Arrange
    const username = 'john.doe';
    const password = 'password';
    const accessToken = 'token';
  
    apiServiceSpy.postLogin.and.returnValue(of({ code:200, access_token: accessToken }));
  
    // Act
    authService.login(username, password);
    tick();
  
    // Assert
    const token = localStorage.getItem('access_token');
    expect(token).toBe(accessToken); // Ensure the token is stored
    localStorage.removeItem('access_token');
  }));
  
  it('should handle login failure', fakeAsync(() => {
    // Arrange
    const username = 'john.doe';
    const password = 'password';
    const expectedError = { status: 422, statusText: 'Validation Error' };
    apiServiceSpy.postLogin.and.returnValue(throwError(()=>expectedError)); 
  
    // Act
    let result: Boolean | undefined;
    authService.login(username, password)
      .then(res => result = res);
    tick();
  
    // Assert
    expect(result).toBe(false);
    expect(apiServiceSpy.postLogin).toHaveBeenCalled();
  }));

  it('delete access_token when log out', fakeAsync(() => {
    // Arrange
    localStorage.setItem('access_token', 'test-token');

    // Act
    authService.logout();
    tick();

    // Assert
    expect(localStorage.getItem('access_token')).toBeNull(); // Ensure the token is removed
  }));


});