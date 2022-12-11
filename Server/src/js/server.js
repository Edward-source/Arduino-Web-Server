//import routes from './src/routes/crmRoutes'

//Creating server
const express = require("express");
//const { default: routes } = require("./src/routes/crmRoutes");
const server = express()
const PORT=3001;

server.set('view engine', 'ejs')


    app.route('/contact')
    server.get((req,res)=>
    res.send("GET req success"))
    server.post((req, res)=>
    res.send("POST req success"))

    app.route('/contact/:contactID')
    server.put.send((req,res)=>
    res.send("PUT req suesss"))
    
    server.delete((req,res)=>
    res.send("Delete req success"))


//routes(server);

server.get("/", (request, response)=>{
    console.log("here");
    response.render("index", {myname :"Edward"});
})

//Start listing ...
server.listen(PORT, ()=> 
console.log(`The server is listining at port number ${PORT}`));