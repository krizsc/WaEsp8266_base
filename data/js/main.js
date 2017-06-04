function loadRecipes(path){
	$.post("request.php",{path: "assets/" + path}, function(data){
		data = JSON.parse(data);
		if(data.status == "OK"){
			recipeArray = JSON.parse(data.contents).recipes;
			$('.container').html("");
			for(i = 0; i < recipeArray.length; i++){
				line = '<ul class="dot">'
				for(j = 0; j < recipeArray[i].ingredients.length; j++){
					line += '<li>' + recipeArray[i].ingredients[j]
				}
				line+='</ul>'
				$('.container').append('<div class="card"> <div class="card-image"> <img src="img/place.jpg"> <span class="card-title black-text">'+ recipeArray[i]["name"] +'</span> </div> <div class="card-content"> <p>'+ line +'</p> </div> <div class="card-action"> <ul class="collapsible" data-collapsible="accordion"> <li> <div class="collapsible-header"><i class="material-icons">reorder</i>Elkészítés</div> <div class="collapsible-body"><span>'+ recipeArray[i]["prepare"] +'</span></div> </li> </ul> </div> </div>');
			}
			$(".collapsible").collapsible();
			console.log("loaded: " + path);
		}
	});
}