export interface ApiPostLogin{
    grant_type: string,
    username: string ,//required
    password: string, //required
    scope: string,
    client_id: string,
    client_secret: string
}