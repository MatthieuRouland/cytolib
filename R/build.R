# Copyright 2019 Fred Hutchinson Cancer Research Center
# See the included LICENSE file for details on the licence that is granted to the user of this software.

# Output the CXX flags. These flags are propagated to sourceCpp via the 
# inlineCxxPlugin (defined below) and to packages via a line in Makevars[.win]
# like this:
#
#  PKG_CXXFLAGS += $(shell "${R_HOME}/bin${R_ARCH_BIN}/Rscript.exe" -e "cytolib::CxxFlags()")
#
CxxFlags <- function() {
   cat(cytolibCxxFlags())
}


#' Output the LD flags for building against cytolib. These flags are propagated
#' to sourceCpp via the inlineCxxPlugin (defined below) and to packages 
#' via a line in Makevars[.win] like this:
#'
#'   PKG_LIBS += $(shell "${R_HOME}/bin${R_ARCH_BIN}/Rscript.exe" -e "cytolib::cytolib_LdFlags()")
#' @export
#' @importFrom RProtoBufLib LdFlags
#' @importFrom RcppParallel RcppParallelLibs
cytolib_LdFlags <- function() {
   cat(cytolibLdFlags())
}

# alias for backward compatibility
cytolibLibs <- function() {
   cytolib_LdFlags()
}


cytolibCxxFlags <- function() {
   
   flags <- c()
   
   
   flags
}

# Return the linker flags requried for cytolib on this platform
cytolibLdFlags <- function() {
   # on Windows and Solaris we need to explicitly link against cytolib.dll
   if ((Sys.info()['sysname'] %in% c("Windows", "SunOS")) && !isSparc()) {
	  res <- asBuildPath(cytolibLibPath())
   } else {
     res <- ""
   }
	# if(all)
	  # res <- paste(res, gslibs)
	res
}

# Determine the platform-specific path to the cytolib library
cytolibLibPath <- function(suffix = "") {
   sysname <- Sys.info()['sysname']
   cytolibSupported <- list(
      "Darwin" = paste("cytolib", suffix, ".so", sep = ""), 
      "Linux" = paste("cytolib", suffix, ".so", sep = ""), 
      "Windows" = paste("libcytolib", suffix, ".a", sep = ""),
      "SunOS" = paste("cytolib", suffix, ".so", sep = "")
   )
   # browser()
   if ((sysname %in% names(cytolibSupported)) && !isSparc()) {
      
      if (sysname == "Windows")
	  {
		  libDir <- "lib/"
         libDir <- paste(libDir, .Platform$r_arch, "/", sep="")
	 }else
		 libDir <- "libs/"
      system.file(paste(libDir, cytolibSupported[[sysname]], sep = ""), 
                  package = "cytolib")
   } else {
      NULL
   }
}

isSparc <- function() {
   Sys.info()['sysname'] == "SunOS" && Sys.info()[["machine"]] != "i86pc"
}

# Helper function to ape the behavior of the R build system
# when providing paths to libraries
asBuildPath <- function(path) {
   if (.Platform$OS.type == "windows") {
      path <- normalizePath(path)
      if (grepl(' ', path, fixed=TRUE))
         path <- utils::shortPathName(path)
      path <- gsub("\\\\", "/", path)
   }
   return(path)
}
