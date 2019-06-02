library(tidyverse)
library(magrittr)
library(igraph)
library(poweRlaw)
library(energy)
read_network <- function(filename, directed, multiple_edge){
	g <- igraph::read_graph(filename, format='edgelist', directed=directed)
	g %<>% igraph::simplify(remove.multiple = multiple_edge)
	return(g)
}
synthethic_data <- function(len, power){
	return(igraph::sample_pa(len, power=power, zero.appeal=1, directed=FALSE) %>% igraph::degree(.))
}
numerical_experiments <- function(graph.degree, synthetic.data){
# density estimation with gaussian kernel  
	dens_est <- density(graph.degree, kernel='gaussian')
	gamma_mle <- poweRlaw::displ$new(graph.degree)
	x_min <- poweRlaw::estimate_xmin(gamma_mle)
	gamma_mle$setXmin(x_min)
# synthetic data preparation for goodness of fist tests
	if(missing(synthetic.data))
		synthethic.data <- synthethic_data(g.len, power=gamma_mle$pars)
# Kolmogorov-Smirnov goodness of fit test 
	ks.result <- ks.test(synthethic.data, graph.degree)
# E-statistic goodness of fit test
	x <- matrix(graph.degree[1:200], nrow=200)
	y <- matrix(synthethic.data[1:200], nrow=200)
	X <- rbind(x, y)
	energy.dist <- dist(X)
	etest.result <- energy::eqdist.etest(energy.dist, sizes=c(200, 200), distance=TRUE, R=199)
	return(list(
		    density=dens_est,
		    gamma_mle=gamma_mle$pars,
		    ks.result=ks.result,
		    etest.result=etest.result)
	)
}





