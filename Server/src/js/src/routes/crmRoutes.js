const routes = (app) =>{
    app.route('/contact')
    .get((req,res)=>
    res.send("GET req success"))
    .post((req, res)=>
    res.send("POST req success"))

    app.route('/contact/:contactID')
    .put.send((req,res)=>
    res.send("PUT req suesss"))
    
    .delete((req,res)=>
    res.send("Delete req success"))
}

export default routes